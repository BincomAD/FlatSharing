--
-- PostgreSQL database dump
--

-- Dumped from database version 14.7 (Ubuntu 14.7-0ubuntu0.22.04.1)
-- Dumped by pg_dump version 14.7 (Ubuntu 14.7-0ubuntu0.22.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: flat; Type: TABLE; Schema: public; Owner: bincom
--

CREATE TABLE public.flat (
    id integer NOT NULL,
    price integer,
    square integer,
    address character varying(255),
    description text,
    owner_id integer
);


ALTER TABLE public.flat OWNER TO bincom;

--
-- Name: flat_id_seq; Type: SEQUENCE; Schema: public; Owner: bincom
--

CREATE SEQUENCE public.flat_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.flat_id_seq OWNER TO bincom;

--
-- Name: flat_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: bincom
--

ALTER SEQUENCE public.flat_id_seq OWNED BY public.flat.id;


--
-- Name: profile; Type: TABLE; Schema: public; Owner: bincom
--

CREATE TABLE public.profile (
    id integer NOT NULL,
    name character varying(255),
    email character varying(255),
    number character varying(255),
    login character varying(255),
    password character varying(255)
);


ALTER TABLE public.profile OWNER TO bincom;

--
-- Name: profile_id_seq; Type: SEQUENCE; Schema: public; Owner: bincom
--

CREATE SEQUENCE public.profile_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.profile_id_seq OWNER TO bincom;

--
-- Name: profile_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: bincom
--

ALTER SEQUENCE public.profile_id_seq OWNED BY public.profile.id;


--
-- Name: rents; Type: TABLE; Schema: public; Owner: bincom
--

CREATE TABLE public.rents (
    id integer NOT NULL,
    owner_id integer,
    client_id integer,
    begin_date date,
    end_date date,
    flat_id integer
);


ALTER TABLE public.rents OWNER TO bincom;

--
-- Name: rents_id_seq; Type: SEQUENCE; Schema: public; Owner: bincom
--

CREATE SEQUENCE public.rents_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.rents_id_seq OWNER TO bincom;

--
-- Name: rents_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: bincom
--

ALTER SEQUENCE public.rents_id_seq OWNED BY public.rents.id;


--
-- Name: smartlock; Type: TABLE; Schema: public; Owner: bincom
--

CREATE TABLE public.smartlock (
    id integer NOT NULL,
    isopen boolean,
    flat_id integer
);


ALTER TABLE public.smartlock OWNER TO bincom;

--
-- Name: smartlock_id_seq; Type: SEQUENCE; Schema: public; Owner: bincom
--

CREATE SEQUENCE public.smartlock_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.smartlock_id_seq OWNER TO bincom;

--
-- Name: smartlock_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: bincom
--

ALTER SEQUENCE public.smartlock_id_seq OWNED BY public.smartlock.id;


--
-- Name: flat id; Type: DEFAULT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.flat ALTER COLUMN id SET DEFAULT nextval('public.flat_id_seq'::regclass);


--
-- Name: profile id; Type: DEFAULT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.profile ALTER COLUMN id SET DEFAULT nextval('public.profile_id_seq'::regclass);


--
-- Name: rents id; Type: DEFAULT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.rents ALTER COLUMN id SET DEFAULT nextval('public.rents_id_seq'::regclass);


--
-- Name: smartlock id; Type: DEFAULT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.smartlock ALTER COLUMN id SET DEFAULT nextval('public.smartlock_id_seq'::regclass);


--
-- Data for Name: flat; Type: TABLE DATA; Schema: public; Owner: bincom
--

COPY public.flat (id, price, square, address, description, owner_id) FROM stdin;
\.


--
-- Data for Name: profile; Type: TABLE DATA; Schema: public; Owner: bincom
--

COPY public.profile (id, name, email, number, login, password) FROM stdin;
\.


--
-- Data for Name: rents; Type: TABLE DATA; Schema: public; Owner: bincom
--

COPY public.rents (id, owner_id, client_id, begin_date, end_date, flat_id) FROM stdin;
\.


--
-- Data for Name: smartlock; Type: TABLE DATA; Schema: public; Owner: bincom
--

COPY public.smartlock (id, isopen, flat_id) FROM stdin;
\.


--
-- Name: flat_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bincom
--

SELECT pg_catalog.setval('public.flat_id_seq', 1, false);


--
-- Name: profile_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bincom
--

SELECT pg_catalog.setval('public.profile_id_seq', 1, false);


--
-- Name: rents_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bincom
--

SELECT pg_catalog.setval('public.rents_id_seq', 1, false);


--
-- Name: smartlock_id_seq; Type: SEQUENCE SET; Schema: public; Owner: bincom
--

SELECT pg_catalog.setval('public.smartlock_id_seq', 1, false);


--
-- Name: flat flat_pkey; Type: CONSTRAINT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.flat
    ADD CONSTRAINT flat_pkey PRIMARY KEY (id);


--
-- Name: profile profile_pkey; Type: CONSTRAINT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.profile
    ADD CONSTRAINT profile_pkey PRIMARY KEY (id);


--
-- Name: rents rents_pkey; Type: CONSTRAINT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.rents
    ADD CONSTRAINT rents_pkey PRIMARY KEY (id);


--
-- Name: smartlock smartlock_pkey; Type: CONSTRAINT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.smartlock
    ADD CONSTRAINT smartlock_pkey PRIMARY KEY (id);


--
-- Name: flat fk_owner_id; Type: FK CONSTRAINT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.flat
    ADD CONSTRAINT fk_owner_id FOREIGN KEY (owner_id) REFERENCES public.profile(id);


--
-- Name: rents rents_client_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.rents
    ADD CONSTRAINT rents_client_id_fkey FOREIGN KEY (client_id) REFERENCES public.profile(id);


--
-- Name: rents rents_flat_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.rents
    ADD CONSTRAINT rents_flat_id_fkey FOREIGN KEY (flat_id) REFERENCES public.flat(id);


--
-- Name: rents rents_owner_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.rents
    ADD CONSTRAINT rents_owner_id_fkey FOREIGN KEY (owner_id) REFERENCES public.profile(id);


--
-- Name: smartlock smartlock_flat_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: bincom
--

ALTER TABLE ONLY public.smartlock
    ADD CONSTRAINT smartlock_flat_id_fkey FOREIGN KEY (flat_id) REFERENCES public.flat(id);


--
-- PostgreSQL database dump complete
--

